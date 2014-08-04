import unittest
import mox


MIN_PRIMARY_KEY_VALUE = 10
HUGE_PRIMARY_KEY = 1000000
TINY_PRIMARY_KEY = 1


class PersistenceException(Exception):
    pass


class BusinessException(Exception):
    pass


class AuditRecord:

    def __init__(self, user):
        self._user = user


class PersonManager(object):

  def __init__(self, person_dao):
    self._dao = person_dao

  def CreatePerson(self, person, user):
    """Creates a Person."""

    if user != 'stevepm':
      raise Exception('no way, jose')

    audit_record = AuditRecord(user)

    try:
      primary_key = self._dao.InsertPerson(person, audit_record)
    except PersistenceException, e:
      raise BusinessException('error talking to db', e)

    if primary_key < MIN_PRIMARY_KEY_VALUE:
      self._dao.DeletePerson(primary_key)
      raise BusinessException('primary key too small')


class PersonDao(object):

  def __init__(self, db):
    self._db = db

  def InsertPerson(self, person, audit_record):
    return db.Execute('INSERT INTO Person(name) VALUES ("%s")' % person)

  def DeletePerson(self, person_id):
    db.Execute('DELETE FROM Person WHERE ...' % person_id)


class PersonManagerTest(unittest.TestCase):

  def setUp(self):
    self.mox = mox.Mox()
    self.dao = self.mox.CreateMock(PersonDao)
    self.manager = PersonManager(self.dao)

  def testCreatePersonWithAccess(self):
    import pdb
    pdb.set_trace()
    self.dao.InsertPerson('test_person', mox.IsA(AuditRecord)).AndReturn(
        HUGE_PRIMARY_KEY)
    self.mox.ReplayAll()
    self.manager.CreatePerson('test_person', 'stevepm')
    self.mox.VerifyAll()

  def testCreatePersonWithSmallPrimaryKey(self):
    self.dao.InsertPerson('test_person', mox.IsA(AuditRecord)).AndReturn(
        TINY_PRIMARY_KEY)
    self.dao.DeletePerson(TINY_PRIMARY_KEY)
    self.mox.ReplayAll()
    self.assertRaises(BusinessException, self.manager.CreatePerson,
                      'test_person', 'stevepm')
    self.mox.VerifyAll()

  def testCreatePersonWithDbException(self):
    self.dao.InsertPerson('test_person', mox.IsA(AuditRecord)).AndRaise(
        PersistenceException('Snakes!'))
    self.mox.ReplayAll()
    self.assertRaises(BusinessException, self.manager.CreatePerson,
                      'test_person', 'stevepm')
    self.mox.VerifyAll()


if __name__ == '__main__':
    unittest.main()
