const button = document.getElementById("subscribed");

button.addEventListener('click', () => {
    const isSubscribed = button.classList.toggle('subscribed');

    button.textCount = isSubscribed ? 'Subscribed ✓' : 'Subscribe';
});