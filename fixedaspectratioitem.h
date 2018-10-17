#ifndef FIXEDASPECTRATIOITEM_H
#define FIXEDASPECTRATIOITEM_H

#include <QLayoutItem>
#include <QLayout>

class FixedAspectRatioItem : public QWidgetItem
{
public:
    FixedAspectRatioItem();
};

class FixedAspectRatioLayout : public QLayout
{
public:
    explicit FixedAspectRatioLayout(QWidget *parent);
    explicit FixedAspectRatioLayout();
    ~FixedAspectRatioLayout() override;

    void addItem(QLayoutItem *item) override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

private:
    QLayoutItem * item;

};
#endif // FIXEDASPECTRATIOITEM_H
