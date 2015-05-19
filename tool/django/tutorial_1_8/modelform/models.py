from django.db import models
from django.forms import ModelForm


TITLE_CHOICES = (
    ('MR', 'Mr.'),
    ('MRS', 'Mrs.'),
    ('MS', 'Ms.'),
)


class Author(models.Model):
  name = models.CharField(max_length=100)
  title = models.CharField(max_length=3, choices=TITLE_CHOICES)
  birth_date = models.DateField(blank=True, null=True)

  def __unicode__(self):
    return self.name


class Book(models.Model):
  name = models.CharField(max_length=100)
  authors = models.ManyToManyField(Author)


# With these models, the ModelForm subclasses above would be roughly
# equivalent to the ones defined in forms.py
class AuthorForm(ModelForm):
  class Meta:
    model = Author
    fields = ['name', 'title', 'birth_date']


class BookForm(ModelForm):
  class Meta:
    model = Book
    fields = ['name', 'authors']
