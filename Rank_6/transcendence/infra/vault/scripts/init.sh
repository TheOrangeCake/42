#!/bin/sh
set -e

export VAULT_ADDR="http://vault:8200"
SECRETS_DIR="/vault/secrets"
KEYS_FILE="/vault/file/vault-keys.json"

mkdir -p "$SECRETS_DIR"

apk add --no-cache jq > /dev/null 2>&1 || true

echo "[vault-init] Waiting for Vault to start..."
until vault status -format=json 2>/dev/null | grep -q '"type"'; do
  sleep 1
done
echo "[vault-init] Vault is reachable."

IS_INIT=$(vault status -format=json 2>/dev/null | jq -r '.initialized')
if [ "$IS_INIT" = "false" ]; then
  echo "[vault-init] Initializing Vault (1 unseal key, threshold 1)..."
  vault operator init -key-shares=1 -key-threshold=1 -format=json > "$KEYS_FILE"
  echo "[vault-init] Vault initialized. Keys saved to persistent volume."
fi

IS_SEALED=$(vault status -format=json 2>/dev/null | jq -r '.sealed')
if [ "$IS_SEALED" = "true" ]; then
  UNSEAL_KEY=$(jq -r '.unseal_keys_b64[0]' "$KEYS_FILE")
  echo "[vault-init] Unsealing Vault..."
  vault operator unseal "$UNSEAL_KEY" > /dev/null
  echo "[vault-init] Vault unsealed."
fi

ROOT_TOKEN=$(jq -r '.root_token' "$KEYS_FILE")
export VAULT_TOKEN="$ROOT_TOKEN"

vault secrets enable -path=secret kv-v2 2>/dev/null && \
  echo "[vault-init] KV v2 engine enabled at secret/." || \
  echo "[vault-init] KV v2 engine already enabled."

echo "[vault-init] Storing secrets in Vault..."

vault kv put secret/postgres \
  POSTGRES_PASSWORD="$SEED_POSTGRES_PASSWORD"

vault kv put secret/auth-service \
  DB_PASSWORD="$SEED_POSTGRES_PASSWORD" \
  FORTYTWO_CLIENT_ID="$SEED_FORTYTWO_CLIENT_ID" \
  FORTYTWO_CLIENT_SECRET="$SEED_FORTYTWO_CLIENT_SECRET" \
  JWT_SECRET="$SEED_JWT_SECRET"

vault kv put secret/group-service \
  DB_PASSWORD="$SEED_POSTGRES_PASSWORD" \
  JWT_SECRET="$SEED_JWT_SECRET"

vault kv put secret/chat-service \
  DB_PASSWORD="$SEED_POSTGRES_PASSWORD" \
  JWT_SECRET="$SEED_JWT_SECRET"

vault kv put secret/api42-postgres \
  POSTGRES_PASSWORD="$SEED_API42_POSTGRES_PASSWORD"

vault kv put secret/api42-service \
  POSTGRES_PASSWORD="$SEED_API42_POSTGRES_PASSWORD" \
  API42_UID="$SEED_FORTYTWO_CLIENT_ID" \
  API42_SECRET="$SEED_FORTYTWO_CLIENT_SECRET" \
  API42_NEXT_SECRET="$SEED_API42_NEXT_SECRET" \
  JWT_SECRET="$SEED_JWT_SECRET"

vault kv put secret/regular-user-postgres \
  POSTGRES_PASSWORD="$SEED_REGULAR_USER_POSTGRES_PASSWORD"

vault kv put secret/regular-user-service \
  POSTGRES_PASSWORD="$SEED_REGULAR_USER_POSTGRES_PASSWORD" \
  REGULAR_USER_JWT_KEY="$SEED_REGULAR_USER_JWT_KEY" \
  REGULAR_USER_EMAIL="$SEED_REGULAR_USER_EMAIL" \
  REGULAR_USER_APP_PASSWORD="$SEED_REGULAR_USER_APP_PASSWORD"

echo "[vault-init] All secrets stored."

echo "[vault-init] Generating per-service env files..."

generate_env() {
  local path="$1"
  local outfile="$2"
  vault kv get -format=json "secret/$path" \
    | jq -r '.data.data | to_entries[] | "\(.key)='"'"'\(.value)'"'"'"' \
    > "$SECRETS_DIR/$outfile"
  echo "[vault-init]   -> $outfile"
}

generate_env "postgres"               "postgres.env"
generate_env "auth-service"           "auth-service.env"
generate_env "group-service"          "group-service.env"
generate_env "chat-service"           "chat-service.env"
generate_env "api42-postgres"         "api42-postgres.env"
generate_env "api42-service"          "api42-service.env"
generate_env "regular-user-postgres"  "regular-user-postgres.env"
generate_env "regular-user-service"   "regular-user-service.env"

echo "[vault-init] All env files generated in $SECRETS_DIR."
echo "[vault-init] Done. Vault is ready."
