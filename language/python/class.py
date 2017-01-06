#!/usr/bin/python

class BaseForm(object):

  def __init__(self, data=None):
    self.data = data
    print 'In BaseForm:', data


class Form(BaseForm):

  def __init__(self, *args, **kwargs):
    if not args and 'data' not in kwargs:
      kwargs['data'] = {}
    print 'In Form:', args, kwargs
    super(Form, self).__init__(*args, **kwargs)


if __name__ == '__main__':
  form1 = Form()
  form2 = Form({'abc', 'cde'})
