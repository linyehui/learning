// For an introduction to the Blank template, see the following documentation:
// http://go.microsoft.com/fwlink/?LinkId=232509
(function () {
    "use strict";

    var app = WinJS.Application;
    var activation = Windows.ApplicationModel.Activation;
    WinJS.strictProcessing();

    app.onactivated = function (args) {
        if (args.detail.kind === activation.ActivationKind.launch) {
            if (args.detail.previousExecutionState !== activation.ApplicationExecutionState.terminated) {
                // TODO: This application has been newly launched. Initialize
                // your application here.
            } else {
                // TODO: This application has been reactivated from suspension.
                // Restore application state here.

                // Retrieve our greetingOutput session state info, 
                // if it exists. 
                var outputValue = WinJS.Application.sessionState.greetingOutput;
                if (outputValue) {
                    var greetingOutput = document.getElementById("greetingOutput");
                    greetingOutput.innerText = outputValue;
                }
            }

            // Restore the user name.
            var localSettings = Windows.Storage.ApplicationData.current.localSettings;
            var userName = localSettings.values["userName"];
            if (userName) {
                var nameInput = document.getElementById("nameInput");
                nameInput.value = userName;
            }

            args.setPromise(WinJS.UI.processAll());

            // Retrieve the button and register our event handler. 
            var helloButton = document.getElementById("helloButton");
            helloButton.addEventListener("click", buttonClickHandler, false);

            // Retrieve the input element and register our
            // event handler.
            var nameInput = document.getElementById("nameInput");
            nameInput.addEventListener("change", nameInputChanged);

        }
    };


    app.oncheckpoint = function (args) {
        // TODO: This application is about to be suspended. Save any state
        // that needs to persist across suspensions here. You might use the
        // WinJS.Application.sessionState object, which is automatically
        // saved and restored across suspension. If you need to complete an
        // asynchronous operation before your application is suspended, call
        // args.setPromise().

        // Store the greeting output for this session. 
        var greetingOutput = document.getElementById("greetingOutput");
        WinJS.Application.sessionState.greetingOutput = greetingOutput.innerText;
    };

    function buttonClickHandler(eventInfo) {

        var userName = document.getElementById("nameInput").value;
        var greetingString = "Hello, " + userName + "!";
        document.getElementById("greetingOutput").innerText = greetingString;
    }

    function nameInputChanged(eventInfo) {
        var nameInput = eventInfo.srcElement;

        // Store the user's name for multiple sessions.
        var appData = Windows.Storage.ApplicationData.current;
        var localSettings = appData.localSettings;
        localSettings.values["userName"] = nameInput.value;
    }

    app.start();
})();
