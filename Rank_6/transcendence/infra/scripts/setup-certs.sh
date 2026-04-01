#!/usr/bin/env bash
set -e

CERT_DIR="infra/nginx"
CERT_FILE="$CERT_DIR/localhost.pem"
KEY_FILE="$CERT_DIR/localhost-key.pem"

if [ -f "$CERT_FILE" ] && [ -f "$KEY_FILE" ]; then
  echo "✅ Certificats déjà présents"
  exit 0
fi

echo "🔐 Certificats absents, génération en cours..."

if ! command -v openssl >/dev/null 2>&1; then
  echo "❌ openssl n'est pas installé"
  exit 1
fi

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -keyout "$KEY_FILE" \
  -out "$CERT_FILE" \
  -subj "/CN=localhost" \
  -addext "subjectAltName=DNS:localhost,IP:127.0.0.1,IP:::1" \
  2>/dev/null

chmod 644 "$KEY_FILE"

echo "✅ Certificats générés avec succès"
