var pedals = []

function initPedals() {
    pedals = []
    for (var i = 0; i < 10; i++) {
        pedals.push({
            pedal: null,
            component: null
        })
    }
}

function createPedalObjects(pedalType, parentObject, index) {
    if (pedals[index].pedal) {
        pedals[index].pedal.destroy()
        pedals[index].pedal = null
        pedals[index].component = null
    }

    var component

    if (pedalType === "Distortion") {
        component = Qt.createComponent("../UIDistortionPedal.qml")
    } else if (pedalType === "Delay") {
        component = Qt.createComponent("../UIDelayPedal.qml")
    }

    if (component.status === Component.Error) {
        console.log(component.errorString())
        return null
    }

    var pedal = component.createObject(parentObject, {x: 0, y: 0});

    if (!pedal) {
        console.log("Error creating pedal")
        return null
    }

    pedals[index].pedal = pedal
    pedals[index].component = component

    return pedal
}

function deletePedal(index) {
    var slot = pedals[index]

    if (!slot || !slot.pedal)
        return

    slot.pedal.destroy()
    slot.pedal = null
    slot.component = null
}
