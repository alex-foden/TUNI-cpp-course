#ifndef SPLASHANIMATION_HH
#define SPLASHANIMATION_HH

#include "gameboard.hh"
#include "splashitem.hh"

#include <QVariantAnimation>

class SplashAnimation : public QVariantAnimation
{
public:
    SplashAnimation(GameBoard* scene, QPointF startPoint, QPointF endPoint);
    ~SplashAnimation();

    // Updates the splash movement.
    void updateCurrentValue(QVariant const& value) override;

private:
    // The scene where the animation takes place.
    GameBoard* scene_;

    // The item to use for the animation.
    SplashItem item_;
};

#endif // SPLASHANIMATION_HH
