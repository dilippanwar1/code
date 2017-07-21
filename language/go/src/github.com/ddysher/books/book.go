package books

import "encoding/json"

type Book struct {
	Title  string `json:title`
	Author string `json:author`
	Pages  int    `json:pages`
}

func NewBookFromJSON(bookJson string) (Book, error) {
	var book Book
	err := json.Unmarshal([]byte(bookJson), &book)
	return book, err
}

func (b *Book) CategoryByLength() string {
	if b.Pages > 300 {
		return "NOVEL"
	} else {
		return "SHORT STORY"
	}
}

func (b *Book) AuthorName() string {
	return b.Author
}
