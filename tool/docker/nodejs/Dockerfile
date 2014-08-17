# Pull base image
FROM ubuntu:14.04
# Install Node.js and npm
RUN apt-get -qq update
RUN apt-get -qqy install -y nodejs npm
# Bundle app source
COPY . /src
# Install app dependencies
RUN cd /src; npm install
# Your app binds to port 8080 so you'll use the EXPOSE
# instruction to have it mapped by the docker daemon.
EXPOSE  8080
# The command to execute when run the image.
CMD ["nodejs", "/src/index.js"]


# Build the image using
#   sudo docker build -t <your username>/centos-node-hello .

# Run the image using
#   sudo docker run -p 49160:8080 -d <your username>/centos-node-hello
