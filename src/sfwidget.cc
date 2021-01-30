#include "sfwidget.h"
#include <qtr2doptionmenu.h>

//-------------------------------------------------------------------------------------------------
SfWidget::SfWidget(QWidget *parent)
 : Qtr2dWidget(parent)
 , mCamera(&mGame)
 , mMenuStyle(1,QPen(Qt::blue), QBrush(Qt::white))
{
    setCamera(&mCamera);
    setWindowTitle("Skifree Deluxe");

    connect(&mGame,SIGNAL(playerCreated(const Qtr2dObject*)), &mCamera, SLOT(followObject(const Qtr2dObject*)));
    connect(&mGame,SIGNAL(requestPlayerSelection()), this, SLOT(resetGame()));

    mCamera.setFieldOfViewMode(Qtr2dCamera::NativeFov);
    mCamera.lookTo(0,0);

    resetGame();
}

//-------------------------------------------------------------------------------------------------
void SfWidget::resetGame()
{

    mGame.init();

    QStringList playerNames = mGame.playerList();
    Q_ASSERT(!playerNames.isEmpty());
    Qtr2dMenuOptions playerOptions;
    foreach(QString playerName, playerNames) {
        playerOptions << Qtr2dMenuOption(playerName,font());
    }

    Qtr2dOptionMenu *menu = new Qtr2dOptionMenu(mMenuStyle, playerOptions);
    setMenu(menu);


}

