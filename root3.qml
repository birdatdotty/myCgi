import Service 1.0
import DefaultRouter 1.0

Service {
    id: main
    root: "/home/2.old/"
    // Глубина стека запросов
    queue: 400
    // Задаем socket
    cgi: ":9000"
    threads: 16

    objGlob: ObjGlob {
        id: obj
        chunks: main.root + "/chunks/"
        scripts: "/home/2.old/scripts"
    }

    RouterCSS {
        root: main.root
        url: "/css"
    }
    RouterJS {
        root: main.root;
        url: "/js"
    }
//    RouterPost {
//        root: main.root;
//        url: "/post"
//    }

    Router {
        root: main.root + "/html";
        url: "/";
        defaultPage: "index.html"
    }
}

/*
post:
page = new Page(Page.HTML, "Hello, world!")

page.out()
*/
