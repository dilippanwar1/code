# http://blog.sae.sina.com.cn/archives/2438

class NGram(object):
    def __init__(self, text, n=3):
        self.length = None
        self.n = n
        self.table = {}
        self.parse_text(text)

    def parse_text(self, text):
        # initial sequence of spaces with length n
        chars = ' ' * self.n
        for letter in (" ".join(text.split()) + " "):
            # append letter to sequence of length n
            chars = chars[1:] + letter
            # increment count
            self.table[chars] = self.table.get(chars, 0) + 1

    def calculate_length(self):
        """ Treat the N-Gram table as a vector and return its scalar magnitude
        to be used for performing a vector-based search.
        """
        self.length = sum([x * x for x in self.table.values()]) ** 0.5
        return self.length

    def __sub__(self, other):
        """ Find the difference between two NGram objects by finding the cosine
        of the angle between the two vector representations of the table of
        N-Grams. Return a float value between 0 and 1 where 0 indicates that
        the two NGrams are exactly the same.
        """
        if not isinstance(other, NGram):
            raise TypeError("Can't compare NGram with non-NGram object.")

        if self.n != other.n:
            raise TypeError("Can't compare NGram objects of different size.")

        total = 0
        for k in self.table:
            total += self.table[k] * other.table.get(k, 0)

        return 1.0 - (float(total) )/ (float(self.length) * float(other.length))

    def find_match(self, languages):
        """ Out of a list of NGrams that represent individual languages, return
        the best match.
        """
        return min(languages, lambda n: self - n)
