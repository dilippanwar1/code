# https://docs.djangoproject.com/en/1.8/topics/db/models/
from django.db import models


class Question(models.Model):
  # Each model is represented by a class that subclasses django.db.models.Model.
  # Each model has a number of class variables, each of which represents a
  # database field in the model. Each field is represented by an instance of a
  # Field class. Some Field classes have required arguments. CharField, for
  # example, requires that you give it a max_length. A Field can also have
  # various optional arguments; in this case, we've set the default value of
  # votes to 0.
  # Note here Django add a default Manager, similar to
  # objects = models.Manager()
  question_text = models.CharField(max_length=200)
  pub_date = models.DateTimeField('date published')

  def __unicode__(self):
    return self.question_text


class Choice(models.Model):
  question = models.ForeignKey(Question)
  choice_text = models.CharField(max_length=200)
  votes = models.IntegerField(default=0)

  def __unicode__(self):
    return self.choice_text

  def was_published_recently(self):
    return self.pub_date >= timezone.now() - datetime.timedelta(days=1)
