package main

import (
	"context"
	"encoding/json"
	"log"
	"net/http"

	"golang.org/x/oauth2"
)

var (
	config = oauth2.Config{
		ClientID:     "222222",
		ClientSecret: "22222222",
		Scopes:       []string{"all"},
		RedirectURL:  "http://localhost:9094/oauth2",
		Endpoint: oauth2.Endpoint{
			AuthURL:  "http://localhost:9096/authorize",
			TokenURL: "http://localhost:9096/token",
		},
	}
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		// This will return auth url from server; which is
		//   http://localhost:9096/authorize
		// in our example. 'xyz' is a random string to prevent CSRF attack.
		// The final url returned from AuthCodeURL is:
		//   http://localhost:9096/authorize?client_id=222222&redirect_uri=http%3A%2F%2Flocalhost%3A9094%2Foauth2&response_type=code&scope=all&state=xyz
		u := config.AuthCodeURL("xyz")
		http.Redirect(w, r, u, http.StatusFound)
	})

	// '/oauth2' endpoint is called by server redirection, see '/authorize'
	// endpoint in server.go.
	http.HandleFunc("/oauth2", func(w http.ResponseWriter, r *http.Request) {
		r.ParseForm()
		state := r.Form.Get("state")
		if state != "xyz" {
			http.Error(w, "State invalid", http.StatusBadRequest)
			return
		}
		code := r.Form.Get("code")
		if code == "" {
			http.Error(w, "Code not found", http.StatusBadRequest)
			return
		}
		// This will call TokenURL, i.e. "http://localhost:9096/token". Token here
		// contains access token, refresh token.
		token, err := config.Exchange(context.Background(), code)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		e := json.NewEncoder(w)
		e.SetIndent("", "  ")
		e.Encode(*token)
	})

	log.Println("Client is running at 9094 port.")
	log.Fatal(http.ListenAndServe(":9094", nil))
}
