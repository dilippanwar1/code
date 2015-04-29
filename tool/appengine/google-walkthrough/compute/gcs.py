#!/usr/bin/python

from apiclient.discovery import build
from oauth2client.gce import AppAssertionCredentials
import httplib2

from apiclient.http import MediaFileUpload

# The mimetype for WAV files
WAV_TYPE = 'audio/wav'
# The name of your Cloud Storage bucket
BUCKET = 'deyuan-walkthrough'

def write_to_storage(file_path):
  '''YOUR CODE HERE'''
  base_url = 'https://www.googleapis.com/auth/'
  full_url = base_url + 'devstorage.full_control'
  service = build(
    'storage', 'v1',
    AppAssertionCredentials(full_url).authorize(
      httplib2.Http()))
  media = MediaFileUpload(file_path,
  mimetype=WAV_TYPE)
  service.objects().insert(
    bucket=BUCKET, name=file_path, media_body=media).execute()
