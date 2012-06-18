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
            }
            args.setPromise(WinJS.UI.processAll());
        }

        //document.addEventListener("DOMContentLoaded", contentLoadedHandler);
    };

    app.oncheckpoint = function (args) {
        // TODO: This application is about to be suspended. Save any state
        // that needs to persist across suspensions here. You might use the
        // WinJS.Application.sessionState object, which is automatically
        // saved and restored across suspension. If you need to complete an
        // asynchronous operation before your application is suspended, call
        // args.setPromise().
    };

    app.start();

    function contentLoadedHandler() {
        WinJS.Application.addEventListener("activated", activatedHandler);
    }

    function activatedHandler() {
        var input = document.getElementById("inUrl");
        input.addEventListener("change", changeHandler);
    }

    function changeHandler(e) {
        var input = e.target;
        var resDiv = document.getElementById("divResult");

        WinJS.xhr({ url: e.target.value }).then(
            function fulfilled(result) {
                if (result.status === 200) {
                    resDiv.style.backgroundColor = "lightGreen";
                    resDiv.innerText = "Success";
                }
            },
            function error(e) {
                resDiv.style.backgroundColor = "red";

                if (e.message != undefined) {  // If the URL is really malformed or blank.
                    resDiv.innerText = e.message;
                }
                else if (e.statusText != undefined) { // If an XmlHttpRequest is made.
                    resDiv.innerText = e.statusText;
                }
                else {
                    resDiv.innerText = "Error";
                }
            });
    }

    document.addEventListener("DOMContentLoaded", contentLoadedHandler, false);
})();
