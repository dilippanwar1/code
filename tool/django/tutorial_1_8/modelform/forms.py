# https://docs.djangoproject.com/en/1.8/topics/forms/
from django import forms


# In a similar way that a model class's fields map to database fields, a form
# class's fields map to HTML form <input> elements.  In a model, you have:
#   class Author(models.Model):
#     name = models.CharField(max_length=100)
# while in a form you have:
#   class AuthorForm(forms.Form):
#     name = forms.CharField(max_length=100)
#
# A form field is represented to a user in the browser as an HTML "widget" - a
# piece of user interface machinery. Each field type has an appropriate default
# Widget class, but these can be overridden as required.
#
# A Form instance has an is_valid() method, which runs validation routines for
# all its fields. When this method is called, if all fields contain valid data,
# it will:
#   return True
#   place the form's data in its cleaned_data attribute.
#
# The distinction between Bound and unbound forms is important:
# An unbound form has no data associated with it. When rendered to the user, it
# will be empty or will contain default values. A bound form has submitted data,
# and hence can be used to tell if that data is valid. If an invalid bound form
# is rendered, it can include inline error messages telling the user what data
# to correct. The form’s is_bound attribute will tell you whether a form has
# data bound to it or not.

class AuthorForm(forms.Form):
  # The field's maximum allowable length is defined by max_length. This does two
  # things. It puts a maxlength="100" on the HTML <input> (so the browser should
  # prevent the user from entering more than that number of characters in the
  # first place). It also means that when Django receives the form back from the
  # browser, it will validate the length of the data.
  name = forms.CharField(max_length=100)
  title = forms.CharField(
      max_length=3, widget=forms.Select(choices=TITLE_CHOICES))
  birth_date = forms.DateField(required=False)


class BookForm(forms.Form):
  name = forms.CharField(max_length=100)
  authors = forms.ModelMultipleChoiceField(queryset=Author.objects.all())


class NameForm(forms.Form):
  your_name = forms.CharField(label='Your name', max_length=100)


class ContactForm(forms.Form):
  subject = forms.CharField(max_length=100)
  message = forms.CharField(widget=forms.Textarea)
  sender = forms.EmailField()
  cc_myself = forms.BooleanField(required=False)
