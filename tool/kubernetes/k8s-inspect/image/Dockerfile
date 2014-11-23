#
# k8s-inspect Dockerfile
#
# Build the image using:
#   sudo docker build -t ddysher/k8s-inspect .
#
# Push the image (docker login first):
#   sudo docker push ddysher/k8s-inspect
#
# Run the image using:
#   sudo docker run -d ddysher/k8s-inspect


FROM dockerfile/python

RUN pip install netifaces

COPY . /k8s-inspect
WORKDIR /k8s-inspect

CMD ["python", "inspector.py"]
