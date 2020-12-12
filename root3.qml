import Service 1.0

import DefaultRouter 1.0
import RouterMySass 1.0

Service {
    id: main
    root: "/home/2.old/" // путь, который используется далее

    cgi: ":9000" // Задаем socket
    queue: 400 // Глубина стека запросов
    threads: 8 // кол-во потоков обрабатывающих запрос

    objGlob: ObjGlob {
        id: obj
        chunks: main.root + "/chunks/"
        scripts: main.root + "/scripts/"
    }

    RouterHTML {
        root: main.root
        url: "/t/"
    }
    RouterCSS {
        root: main.root
        url: "/css/"
    }
    RouterHTML {
        type: Page.JSON
        root: main.root;
        url: "/json/";
        defaultPage: "1.json"
    }
    RouterJS {
        root: main.root;
        url: "/js/"
    }
    RouterPost {
        root: main.root;
        url: "/post/"
    }

//    RouterHTML {
    RouterChunk {
        root: main.root
        url: "/chunks/"
    }

    RouterMySass {
        root: main.root;
        url: "/sass/";
        defaultPage: "1.sass"
    }

    RouterHTML {
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
