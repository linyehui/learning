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
        document.getElementById("btnDownload").addEventListener("click", clickBtnDownload, false);
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
        WinJS.Promise.onerror = errorHandler
    }

    // ver 1.0
    function changeHandler(e) {
        var input = e.target;
        var resDiv = document.getElementById("divResult");
        var twoDiv = document.getElementById("div2");

        WinJS.xhr({ url: e.target.value })
            .then(function (result) {
                if (result.status === 200) {
                    resDiv.style.backgroundColor = "lightGreen";
                    resDiv.innerText = "Success";
                }
            })
            .then(function (result) {
                if (result.status === 200) {
                    twoDiv.style.backgroundColor = "yellow";
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

    /* ver 2.0 for test error
    function changeHandler(e) {
        var input = e.target;
        var resDiv = document.getElementById("divResult");
        var twoDiv = document.getElementById("div2");

        WinJS.xhr({ url: e.target.value });
    }
    */

    function errorHandler(event) {
        var ex = event.detail.exception;
        var promise = event.detail.promise;
    }

    function clickBtnDownload() {
        // Assign the URI to download from.
        var uriExample = new Windows.Foundation.Uri("http://www.microsoft.com");
        var progressDiv = document.getElementById("divProgress");

        // Get the folder for temporary files.
        var tempFolder = Windows.Storage.ApplicationData.current.temporaryFolder;

        // Create the temp file asynchronously.
        tempFolder.createFileAsync("tempfile.txt", Windows.Storage.CreationCollisionOption.ReplaceExisting)
           .then(function (tempFile) {
               // The createFileAsync call succeeded, so start the download operation.
               var downloader = new Windows.Networking.BackgroundTransfer.BackgroundDownloader();
               var transfer = downloader.createDownload(uriExample, tempFile);
               return transfer.startAsync();
           })
           .then(
               //Define the function to use when the download completes successfully
               function (result) {
                   console.log("File download complete.");
                   progressDiv.innerText += "\nFile download complete.";
               },
               // Define the error handling function.
               function (error) {
                   console.log("File download failed.");
                   progressDiv.innerText += "\nFile download failed.";
               },
               // Define the progress handling function.
               function (progress, resultSoFar) {
                   console.log("Bytes retrieved: " + progress.bytesReceived);
                   progressDiv.innerText = "Bytes retrieved: " + progress.progress.bytesReceived;
               });

    }

    document.addEventListener("DOMContentLoaded", contentLoadedHandler, false);
})();
