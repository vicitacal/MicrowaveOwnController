#include "EncButton.h"
#include "ControllerState.h"
#include "Property.h"
#include "Time.h"

class OvenController {

public:

    Time CurrentTime;

    Property<ControllerState> CurrentState;

    OvenController(EncButton enc) : _enc(enc) {

    }

    void Tick() {

        if (_enc.getAction() == EBAction::None) { return; }
        
    }

private:

    EncButton _enc;

};
