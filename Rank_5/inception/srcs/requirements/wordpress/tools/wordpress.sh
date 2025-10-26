#! /bin/ash

# stop if setup fail
set -e

# Download and install wp-cli
if ! command -v wp >/dev/null 2>&1; then
	curl -L -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x /usr/local/bin/wp
fi

mkdir -p /var/www/html
cd /var/www/html

# config port 9000
if [ ! -e /etc/.setup ]; then
	sed -i 's/listen = 127.0.0.1:9000/listen = 9000/g' /etc/php83/php-fpm.d/www.conf
	touch /etc/.setup
fi

# Install and configure wordpress
if [ ! -e /.setup1 ]; then
	until  mariadb-admin ping --protocol=tcp --host=mariadb -u "$MARIADB_USER" --password="$MARIADB_PASSWORD" --wait >/dev/null 2>/dev/null; do
		sleep 1
	done

	if [ ! -f wp-config.php ]; then
		echo "memory_limit = 512M" >> /etc/php83/conf.d/99-memory-limit.ini
		wp core download --allow-root
		wp config create --allow-root \
			--dbhost=mariadb \
			--dbuser="$MARIADB_USER" \
			--dbpass="$MARIADB_PASSWORD" \
			--dbname="$MARIADB_DATABASE"
		wp core install --allow-root \
			--url="hoannguy.42.fr" \
			--title="$WORDPRESS_TITLE" \
			--admin_user="$WORDPRESS_ADMIN_USER" \
			--admin_password="$WORDPRESS_ADMIN_PASSWORD" \
			--admin_email="$WORDPRESS_ADMIN_EMAIL"

		if ! wp user get "$WORDPRESS_USER" --allow-root > /dev/null 2>&1; then
			wp user create "$WORDPRESS_USER" "$WORDPRESS_EMAIL" --role=author --user_pass="$WORDPRESS_PASSWORD" --allow-root
		fi
	fi
	chmod o+w -R /var/www/html/wp-content
	touch .setup1
fi

exec "$@"
