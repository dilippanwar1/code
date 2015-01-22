# Experiment with importlib.

import importlib


def load_class(full_class_string):
  """Dynamically load a class from a string."""

  class_data = full_class_string.split(".")
  module_path = ".".join(class_data[:-1])
  class_str = class_data[-1]

  module = importlib.import_module(module_path)
  # Finally, we retrieve the Class
  return getattr(module, class_str)


NoneClass = load_class('pkg_importlib_mod.main.NoneClass')
NoneObject = NoneClass()
NoneObject.PrintMe()
