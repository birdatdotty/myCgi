import Service 1.0
import DefaultRouter 1.0

Service {
    id: main
    root: "/home/2.old/" // путь, который используется далее

    cgi: ":9000" // Задаем socket
    queue: 400 // Глубина стека запросов
    threads: 8 // кол-во потоков обрабатывающих запрос

    objGlob: ObjGlob {
        id: obj
        chunks: main.root + "/chunks/"
        scripts: main.root + "/scripts"
    }

    RouterCSS {
        root: main.root
        url: "/css"
    }
    RouterJS {
        root: main.root;
        url: "/js"
    }
    RouterPost {
        root: main.root;
        url: "/post"
    }

    Router {
        root: main.root
        url: "/chunks"
    }

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
