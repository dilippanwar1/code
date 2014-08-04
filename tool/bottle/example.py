from bottle import route, run, template

# 'route' is a function created by make_default_app_wrapper(), which is defined
# in bottle.py.  At compile time, index is redefiend by whatever is returned by
# route function.  Initially, interpreter call @route with string parameter
# '/hello/<name>', the call actually goes to wrapper(*a, *ka) in make_default_xx.
# As we can see from that function, the name attribute of app() gets called,
# and this lead us to route method defined in class Bottle().  At this point,
# we call route with path='/hello/<name>', since @route('/hello/<name>') has
# parameter, whatever returned by route will be used as true decorator (By true
# decorator, it means whatever returned by it will be used to rebind to index).
# Current call to route will return decorator defined inside route, and this
# will be used as true decorator; therefore, immediately after route returns
# decorator() function, the function will be called, with index() as its callback.
# In decorator, bottle instantiate several Route classes, and return index()
# itself.  After this, all future call to index() will call index() itself.
@route('/hello/<name>')
def index(name):
    return template('<b>Hello {{name}}</b>!', name=name)

@route('/greet')
def index2():
    import pdb
    pdb.set_trace()
    return template('index.html', basket=['apple', 'banana', 'orange'])

# Since we don't specify which server to use, the default WSGIRefServer will be
# used, it is a small reference server distributed with python, located at
# "/usr/lib/python2.7/wsgiref/".  This server will handle WSGI communication,
# and pass to our application by calling app directly.  Therefore, Bottle
# defines __call__() in order to get request from WSGIRefServer.  The function
# is passed to two parameters, one is 'environ', the other is 'start_response'.
# The Bottle will do url matching, call index() defined above, etc.
run(host='localhost', port=8080)
