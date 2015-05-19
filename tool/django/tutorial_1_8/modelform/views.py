from django.shortcuts import render
from django.http import HttpResponseRedirect

from .forms import NameForm


def get_name(request):
  # If this is a POST request we need to process the form data
  if request.method == 'POST':
    # Create a form instance and populate it with data from the request:
    # This is called "binding data to the form" (it is now a bound form).
    form = NameForm(request.POST)
    # Check whether it's valid:
    if form.is_valid():
      # Process the data in form.cleaned_data as required
      # ...
      # Redirect to a new URL:
      return HttpResponseRedirect('/thanks/')
  # If a GET (or any other method) we'll create a blank form:
  else:
    form = NameForm()
  # All you need to do to get your form into a template is to place the form
  # instance into the template context. So if your form is called form in the
  # context, {{ form }} will render its <label> and <input> elements. There
  # are other output options though for the <label>/<input> pairs:
  #   {{ form.as_table }} will render them as table cells wrapped in <tr> tags
  #   {{ form.as_p }} will render them wrapped in <p> tags
  #   {{ form.as_ul }} will render them wrapped in <li> tags
  # Source code of such conversions are located at:
  #   /usr/local/lib/python2.7/dist-packages/django/forms/forms.py
  #
  # We don’t have to let Django unpack the form’s fields; we can do it manually
  # if we like (allowing us to reorder the fields, for example). Each field is
  # available as an attribute of the form using {{ form.name_of_field }}, and
  # in a Django template, will be rendered appropriately.
  #
  # The as_p(), as_ul() and as_table() methods are simply shortcuts for lazy
  # developers - they're not the only way a form object can be displayed:
  # class BoundField: Used to display HTML or access attributes for a single
  # field of a Form instance.
  # Source code of BoundFields are located at:
  #   /usr/local/lib/python2.7/dist-packages/django/forms/forms.py
  # E.g.
  # >> form = ContactForm()
  # >> form['subject']
  # >>  <django.forms.forms.BoundField at 0x7fd6d71751d0>
  # >> print form['subject']
  # >>  <input id="id_subject" maxlength="100" name="subject" type="text" />
  # >> form['subject'].label_tag()
  # >>  <label for="id_subject">Subject:</label>
  return render(request, 'name.html', {'form': form})
