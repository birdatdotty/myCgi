// Post, upload and Ws inherit Page
import Post 1.0
import Upload 1.0

Router {
  path: "/tmp/unix.socket"
  root: "/var/www/html"

  Path {
    url: "/post"
    page: Post {data: getData}
  }
  Path {
    url: "/upload"
    page: Upload {data: getData; uri: uri}
  }
  Ws {
    url: "/ws"
    page: Ws {}
  }
}
