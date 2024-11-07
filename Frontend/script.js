function vote(candidate) {
    fetch(`/cgi-bin/vote.cgi?vote=${candidate}`)
        .then(response => response.text())
        .then(data => {
            document.getElementById('results').innerHTML = data;
        });
}

function displayResults() {
    fetch('/cgi-bin/vote.cgi')
        .then(response => response.text())
        .then(data => {
            document.getElementById('results').innerHTML = data;
        });
}

document.addEventListener('DOMContentLoaded', displayResults);
