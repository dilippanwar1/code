import arithmetic
import unittest


class TestArithmetic(unittest.TestCase):

  def setUp(self):
    """Per test case"""

  def TestAdd(self):
    self.assertEqual(3, arithmetic.Add(1, 2))


if __name__ == '__main__':
  unittest.main()
