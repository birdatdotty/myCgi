import Service 1.0
import ClassicHTML 1.0


Service {
    id: main
    root: "/home/2/"
    // Глубина стека запросов
    queue: 400
    // Задаем socket
    cgi: ":9000"

    objGlob: ObjGlob {
      id: obj
        threads: 8
        defaultPage: "/index.html"
        chunks: main.root + "/chunks"
        scripts: main.root + "/scripts"
//        posts: main.root + "/posts"
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
        //objGlob: main.objGlob

        root: main.root + "/html";
        url: "/";
        defaultPage: "/index.html"
    }
}

/*
post:
QJSEngine engine;
engine.eval(Script.qj)

Script.qj:
ret.type = "text/css"
ret.body = "* {color: red}"
*/
