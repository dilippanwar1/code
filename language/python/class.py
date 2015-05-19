class BaseForm(object):

  def __init__(self, data=None):
    self.data = data
    print '----------', data


class Form(BaseForm):

  def __init__(self, *args, **kwargs):
    if not args and 'data' not in kwargs:
      kwargs['data'] = {}
    print args
    print kwargs
    super(Form, self).__init__(*args, **kwargs)


form = Form({'abc', 'cde'})
