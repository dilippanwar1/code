#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import cgi
import os
import jinja2
import webapp2
import time
import datetime

from google.appengine.ext import db
from google.appengine.api import users
from google.appengine.api import taskqueue
from google.appengine.api import rdbms


def create_parent_key():
  return db.Key.from_path('ParentKind', 'parentId')


class Worker(webapp2.RequestHandler):
  def post(self):
    time.sleep(30)
    comments = db.GqlQuery('SELECT * FROME Comment')
    for comment in comments:
      comment.moderated = datetime.datetime.now()
      comment.put()


class Comment(db.Model):
  content = db.StringProperty(multiline=True)
  date = db.DateTimeProperty(auto_now_add=True)
  moderated = db.DateTimeProperty()


class SendHandler(webapp2.RequestHandler):
  def post(self):
    comment = Comment(parent=create_parent_key())
    comment.content = self.request.get('comment')
    comment.put()
    taskqueue.add(url='/worker')
    self.redirect('/')


class MainHandler(webapp2.RequestHandler):
  def get(self):
    connection = rdbms.connect(
      instance='uplifted-plate-93013:walkthrough',
      database='walkthrough')
    cursor = connection.cursor()
    cursor.execute('SELECT * FROM comments')
    sqlcomments = cursor.fetchall()
    user = users.get_current_user()
    names = ['Doogle', 'Akshay']
    names.append(user)
    comments = db.GqlQuery(
      'SELECT * FROM Comment WHERE ANCESTOR IS :1 '
      'ORDER BY date DESC LIMIT 10',
      create_parent_key())
    template_data = {
      'names': names,
      'comments': comments,
      'sqlcomments': sqlcomments
    }
    template = jinja_environment.get_template('index.html')
    self.response.write(template.render(template_data))


jinja_environment = jinja2.Environment(
  loader=jinja2.FileSystemLoader(
    os.path.dirname(__file__)))


app = webapp2.WSGIApplication([
  ('/', MainHandler), ('/send', SendHandler), ('/worker', Worker)
], debug=True)
