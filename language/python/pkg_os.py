import os

# Cann't set boolean.
if False:
  os.environ.setdefault('BYPASS_ME', False)

print os.environ.get('BYPASS_ME')
