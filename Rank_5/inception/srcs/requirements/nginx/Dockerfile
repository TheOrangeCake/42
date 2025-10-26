FROM alpine:3.21

RUN apk update
RUN apk add nginx \
			openssl
RUN mkdir -p /etc/nginx/ssl

COPY ./tools/nginx.sh /tmp/nginx.sh
COPY ./conf/nginx.conf /etc/nginx/nginx.conf
RUN chmod +x /tmp/nginx.sh
ENTRYPOINT ["ash", "/tmp/nginx.sh"]

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]

# Flow:
# Install nginx
# Install TLS for HTTPS
# Replace the nginx config file
# Setup TLS through script
# Run nginx in docker