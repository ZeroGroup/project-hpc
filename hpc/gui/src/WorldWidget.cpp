#include "WorldWidget.hpp"

WorldWidget::WorldWidget(QWidget * parent)
    : QWidget(parent) {

    QHBoxLayout * layout = new QHBoxLayout();
//    QToolBox * tb = new QToolBox(this);
//    tb->addAction(new QAction(QIcon(":/icons/new.png"),"new", this));
//    tb->addItem(new QLabel("aaa"), QIcon(":/icons/new.png"), "bbb");
//    layout->addWidget(tb);
    layout->addWidget(new QLabel("World, buahahaha!"), 1);
    this->setLayout(layout);
}

WorldWidget::~WorldWidget(){

}

