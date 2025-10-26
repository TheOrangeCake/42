FROM alpine:3.21

RUN apk update
RUN apk add mariadb mariadb-client

COPY ./tools/mariadb.sh /tmp/mariadb.sh
RUN chmod +x /tmp/mariadb.sh
ENTRYPOINT ["ash", "/tmp/mariadb.sh"]

EXPOSE 3306

CMD ["mariadbd-safe"]

# Flow:
# Install mariadb
# Setup mariadb through script
# -> change config to accept all connection
# -> create a new database if not existed yet
# --> install a new database
# --> start a temp server
# --> create a new database
# --> create and setup users in that new database
# --> stop the temp server
# run mariadb in docker

# Test:
# docker build -t mariadb .
# docker run --name mariadb --rm --env-file ../../.env -p 3306:3306 -d mariadb
# docker exec -it mariadb ash
# -> mariadb -u root -p
# -> SHOW DATABASES;
# -> exit;
# -> mariadb -u hoannguy -p
# -> SHOW DATABASES;