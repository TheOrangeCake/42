#! /bin/ash

# stop if setup fail
set -e

if [ ! -e /etc/.setup ]; then
	openssl req -x509 -days 365 -newkey rsa:2048 -nodes \
		-out '/etc/nginx/ssl/inception.crt' \
		-keyout '/etc/nginx/ssl/inception.key' \
		-subj "/CN=hoannguy.42.fr" \
		>/dev/null 2>/dev/null
	touch /etc/.setup
fi

exec "$@"
