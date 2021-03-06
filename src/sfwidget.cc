#include "sfwidget.h"
#include <qtr2doptionmenu.h>

//-------------------------------------------------------------------------------------------------
SfWidget::SfWidget(QWidget *parent)
 : Qtr2dWidget(parent)
 , mCamera(&mGame)
 , mMenuStyle(/*1,QPen(Qt::blue), QBrush(Qt::white)*/)
{
    setCamera(&mCamera);
    setWindowTitle("Skifree Deluxe");

    connect(&mGame,SIGNAL(playerCreated(const Qtr2dObject*)), &mCamera, SLOT(followObject(const Qtr2dObject*)));
    connect(&mGame,SIGNAL(requestPlayerSelection()), this, SLOT(resetGame()));

    mCamera.setFieldOfViewMode(Qtr2dCamera::NativeFov);
    mCamera.lookTo(0,0);
    mGame.init();

    resetGame();
}

//-------------------------------------------------------------------------------------------------
void SfWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F2)
        resetGame();
    Qtr2dWidget::keyPressEvent(event);
}

//-------------------------------------------------------------------------------------------------
void SfWidget::resetGame()
{

    mGame.reset();

    QStringList playerNames = mGame.playerList();
    Q_ASSERT(!playerNames.isEmpty());
    Qtr2dMenuOptions playerOptions;
    foreach(QString playerName, playerNames) {
        playerOptions << Qtr2dMenuOption(mGame.playerIcon(playerName), playerName,font());
    }

    Qtr2dOptionMenu *menu = new Qtr2dOptionMenu(mMenuStyle, playerOptions);

    connect(menu, &Qtr2dOptionMenu::selected, this, [&,menu](int index) {
        mGame.reset(menu->option(index).text());
        menu->deleteLater();
    });

    setMenu(menu);
}

