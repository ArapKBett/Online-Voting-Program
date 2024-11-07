function displayResults() {
    fetch('/cgi-bin/vote.cgi')
        .then(response => response.text())
        .then(data => {
            document.getElementById('results').innerHTML = data;
        });
}

setInterval(displayResults, 5000); // Update results every 5 seconds
