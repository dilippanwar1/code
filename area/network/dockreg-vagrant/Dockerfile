FROM ubuntu:trusty

RUN apt-get update && \
    apt-get install -y python python-setuptools nodejs && \
    easy_install supervisor && \
    mkdir /var/log/dockreg

EXPOSE 8000

CMD []
ENTRYPOINT ["/usr/local/bin/supervisord", "-c", "/etc/supervisord.conf"]

ADD supervisord.conf /etc/supervisord.conf
ADD dockreg /usr/bin/dockreg
ADD node-app/server.js /root/server.js

RUN chmod a+x /usr/bin/dockreg
