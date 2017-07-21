// Note, by default, Ginkgo will randomize the order in which your specs (Its) are run.
package books_test

import (
	"fmt"

	. "github.com/ddysher/books"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
)

// The function in the Describe will contain our specs.
var _ = Describe("Book", func() {
	// In order to share state between a 'BeforeEach' and an 'It' you use closure
	// variables, typically defined at the top of the most relevant Describe or
	// Context container.
	var (
		longBook  Book
		shortBook Book
	)

	// The BeforeEach is run before each spec (e.g. 'It') thereby ensuring that
	// each spec has a pristine copy of the state.
	BeforeEach(func() {
		fmt.Fprintf(GinkgoWriter, "This will run for each 'It'")

		longBook = Book{
			Title:  "Les Miserables",
			Author: "Victor Hugo",
			Pages:  1488,
		}

		shortBook = Book{
			Title:  "Fox In Socks",
			Author: "Dr. Seuss",
			Pages:  24,
		}
	})

	// 'Describe' and 'Context' are usually called container in ginkgo; while 'It'
	// is called spec in ginkgo (There is also other specs like 'Specify', which
	// mostly are alias to 'It').
	Describe("Categorizing book length", func() {
		Context("With more than 300 pages", func() {
			It("should be a novel", func() {
				Expect(longBook.CategoryByLength()).To(Equal("NOVEL"))
			})
		})

		Context("With fewer than 300 pages", func() {
			It("should be a short story", func() {
				Expect(shortBook.CategoryByLength()).To(Equal("SHORT STORY"))
			})
		})
	})

	// Since 'Describe' and 'Context' are containers, thus 'It' can be used
	// independent of them, though this is not common. Semantic differences
	// aside, the two container types have identical behavior.
	It("can be read correctly", func() {
		newBook, _ := NewBookFromJSON(
			`{
        "title":"Les Miserables",
        "author":"Victor Hugo",
        "pages":1488
       }`)
		Expect(newBook.Title).To(Equal("Les Miserables"))
		Expect(newBook.Author).To(Equal("Victor Hugo"))
		Expect(newBook.Pages).To(Equal(1488))
	})
})

var _ = Describe("Book", func() {
	var (
		book Book
		err  error
	)

	// When nesting 'Describe/Context' blocks the 'BeforeEach' blocks for all the
	// container nodes surrounding an 'It' are run from outermost to innermost when
	// the 'It' is executed. The same is true for AfterEach block though they run
	// from innermost to outermost. Note: the BeforeEach and AfterEach blocks run
	// for each 'It' block.
	BeforeEach(func() {
		book, err = NewBookFromJSON(
			`{
        "title":"Les Miserables",
        "author":"Victor Hugo",
        "pages":1488
       }`)
	})

	// In general, the only code within a container block should be an It block or
	// a BeforeEach/JustBeforeEach/AfterEach block, or closure variable declarations.
	// It is generally a mistake to make an assertion in a container block.
	// It is also a mistake to initialize a closure variable in a container block.
	// If one of your Its mutates that variable, subsequent Its will receive the
	// mutated value. This is a case of test pollution and can be hard to track down.
	// Always initialize your variables in BeforeEach blocks.
	Describe("loading from JSON", func() {
		Context("when the JSON parses succesfully", func() {
			It("should populate the fields correctly", func() {
				Expect(book.Title).To(Equal("Les Miserables"))
				Expect(book.Author).To(Equal("Victor Hugo"))
				Expect(book.Pages).To(Equal(1488))
			})

			It("should not error", func() {
				Expect(err).NotTo(HaveOccurred())
			})
		})

		Context("when the JSON fails to parse", func() {
			BeforeEach(func() {
				// `book` is overwritten here since this 'BeforeEach' is ran after
				// outermost one. This is not a best practice though.
				book, err = NewBookFromJSON(
					`{
            "title":"Les Miserables",
            "author":"Victor Hugo",
            "pages":1488oops
           }`)
			})

			It("should return the zero-value for the book", func() {
				Expect(book).To(BeZero())
			})

			It("should error", func() {
				Expect(err).To(HaveOccurred())
			})
		})
	})

	Describe("Extracting the author's name", func() {
		It("should correctly identify and return the name", func() {
			Expect(book.AuthorName()).To(Equal("Victor Hugo"))
		})
	})
})

var _ = Describe("Browsing the library", func() {
	BeforeEach(func() {
		By("Fetching a token and logging in")
	})

	// Ginkgo provides 'By' to help make sentence easier to read. The string passed
	// to By is emitted via the GinkgoWriter. If a test succeeds you won’t see any
	// output beyond Ginkgo’s green dot. If a test fails, however, you will see each
	// step printed out up to the step immediately preceding the failure. Running
	// with ginkgo -v always emits all steps.
	It("should be a pleasant experience", func() {
		By("Entering an aisle")
		// Test code

		By("Browsing for books")
		// Test code

		By("Finding a particular book")
		// Test code

		By("Check the book out")
		// Test code
	})
})
