#include <QFontMetrics>
#include "qtr2doptionmenu.h"

#define SPACING 10

//-------------------------------------------------------------------------------------------------
Qtr2dMenuOption::Qtr2dMenuOption(const QPixmap &icon)
 : mIcon(icon)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dMenuOption::Qtr2dMenuOption(const QPixmap &icon, const QString &text, const QFont &font)
 : mIcon(icon), mText(text), mFont(font)
{
}

//-------------------------------------------------------------------------------------------------
Qtr2dMenuOption::Qtr2dMenuOption(const QString &text, const QFont &font)
 : mText(text), mFont(font)
{
}

//-------------------------------------------------------------------------------------------------
QSize Qtr2dMenuOption::size() const
{
    QFontMetrics fm(mFont);
    int width  = mIcon.width() + fm.width(mText);

    if (mIcon.width() > 0 && mText.length() > 0)
        width += SPACING;

    int height = qMax(mIcon.height(),fm.height());


    return QSize(width,height);
}

//-------------------------------------------------------------------------------------------------
//                                     OptionMenu
//-------------------------------------------------------------------------------------------------
Qtr2dOptionMenu::Qtr2dOptionMenu(Qtr2dMenuStyle &style,const Qtr2dMenuOptions &options)
 : Qtr2dMenu(style)
 , mOptions(options)
{
    mCurrentIndex = mOptions.count() > 0 ? 0 : -1;
}

//-------------------------------------------------------------------------------------------------
QSize Qtr2dOptionMenu::size() const
{

    QSize optionSize = optionsMaxSize();

    int optionsSpacing     = (mOptions.count() - 1) * SPACING;
    int optionsTotalHeight = mOptions.count() * optionSize.height() + optionsSpacing;

    return QSize(2*style().border() + 2*style().padding() + optionSize.width() + 2,
                 2*style().border() + 2*style().padding() + optionsTotalHeight);
}

//-------------------------------------------------------------------------------------------------
const Qtr2dMenuOption &Qtr2dOptionMenu::option(int index) const
{
    Q_ASSERT(index >= 0 && index < mOptions.count());
    return mOptions[index];
}

//-------------------------------------------------------------------------------------------------
void Qtr2dOptionMenu::renderContent(QPainter &p, const QSize &boxSize)
{
    p.translate(style().padding() + style().border(),style().padding());
    p.setPen(QPen(Qt::black,1));

    int index = 0;
    QSize optionSize = optionsMaxSize();

    for(const auto &option : mOptions) {
        p.save();
        QRect optionRect = QRect(0,0,optionSize.width(), optionSize.height());
        QPixmap icon = option.icon();
        if (!icon.isNull()) {
            p.drawPixmap(0,0,icon);
            p.translate(icon.width() + style().padding(),0);
        }

        p.drawText(optionRect,Qt::AlignVCenter | Qt::AlignLeft, option.text());
        p.restore();

        if (index == mCurrentIndex) {
            p.save();
            p.setPen(Qt::blue);
            p.drawRect(optionRect);
            p.restore();
        }

        p.translate(0,option.size().height() + SPACING);
        index++;
    }
}

//-------------------------------------------------------------------------------------------------
void Qtr2dOptionMenu::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down) {
        if (mCurrentIndex < mOptions.count()-1)
            mCurrentIndex++;
        else if (mOptions.count() > 0)
            mCurrentIndex = 0;
        emit updateRequest();
    }

    if (event->key() == Qt::Key_Up) {
        if (mCurrentIndex > 0)
            mCurrentIndex--;
        else if (mOptions.count() > 0)
            mCurrentIndex = mOptions.count()-1;
        emit updateRequest();
    }

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space) {
        if (mCurrentIndex >= 0 && mCurrentIndex < mOptions.count()) {
            emit selected(mCurrentIndex);
        }
    }

}

//-------------------------------------------------------------------------------------------------
QSize Qtr2dOptionMenu::optionsMaxSize() const
{
    QSize optionSize;
    for(const auto &option : mOptions) {
        optionSize.setHeight(qMax(optionSize.height(),option.size().height()));
        optionSize.setWidth(qMax(optionSize.width(), option.size().width()));
    }

    return optionSize;
}


