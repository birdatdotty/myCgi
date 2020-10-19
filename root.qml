import Service 1.0
//import RouterCSS 1.0
//import RouterJS 1.0
//import RouterPost 1.0
import ClassicHTML 1.0

//Service {
//    id: main
//    root: "/home/1/"
//    // Глубина стека запросов
//    queue: 400
//    // Задаем socket
//    cgi: ":9000"
//    defaultPage: "/index.html"

//    RouterCSS { root: main.root; url: "/css" }
//    RouterJS { root: main.root; url: "/js" }
//    RouterPost { root: main.root; url: "/post" }
//}

Service {
    id: main
    root: "/home/2/"
    // Глубина стека запросов
    queue: 400
    // Задаем socket
    cgi: ":9000"
    defaultPage: "/index.html"

    Router {
        root: main.root + "/html";
        url: "/";
        defaultPage: "/index.html"

        RouterCSS {
             root: main.root
             url: "/css"
        }
        RouterJS {
            root: main.root;
            url: "/js"
        }
    }
}
