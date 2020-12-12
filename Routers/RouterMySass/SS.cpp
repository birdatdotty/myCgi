#include "SS.h"

#include <QDebug>

SS::SS(int depth, QString line, SS *parent)
    : _parent(parent), _depth(depth), _line(line)
{}

int SS::depth() const {
    return _depth;
}
QString SS::line() const {
    return _line;
}

bool SS::isSelector() const {
    return _line.indexOf(':') == -1;
}

QString SS::selector() {
    if (isSelector()) {
        if (_parent == nullptr)
            return _line + " ";

        return _parent->selector() + _line + " ";
    }
    return "";
}

void SS::setParent(SS *parent) {
    _parent = parent;
}

void SS::addChild(SS *child) {
    children.append(child);
}

void SS::addParam(SS *param) {
    params.append(param);
}

void SS::addSelector(SS *selector) {
    selectors.append(selector);
}

QString SS::css(QString pre) {
    QString ret;
    if (params.size() != 0) {
        ret += pre + _line + " {\n";

        for (SS* param: params)
            ret += "  " + param->line() + ";\n";

        ret += "}\n";
    }
    for (SS* selectorIt: selectors) {
        if (pre.size() > 0)
            ret += selectorIt->css(pre + _line + " ");
        else
            if (_line.size() > 0)
                ret += selectorIt->css(pre + _line + " ");
            else
                ret += selectorIt->css();
    }

    return ret;
}
