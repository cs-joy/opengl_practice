/**
 * contact.js — Submit Contact Us form to the API (stored in MySQL).
 */

document.addEventListener('DOMContentLoaded', () => {
  const form = document.getElementById('contact-form');
  const alertEl = document.getElementById('contact-alert');
  const submitBtn = form?.querySelector('button[type="submit"]');

  if (!form) return;

  form.addEventListener('submit', async (event) => {
    event.preventDefault();

    const payload = Object.fromEntries(new FormData(form).entries());

    if (submitBtn) {
      submitBtn.disabled = true;
    }

    try {
      const result = await clientApi('/public/contact', {
        method: 'POST',
        body: JSON.stringify(payload),
      });
      showClientAlert(
        alertEl,
        result.message || 'Your message was sent successfully.',
        'success'
      );
      form.reset();
    } catch (err) {
      showClientAlert(alertEl, err.message, 'error');
    } finally {
      if (submitBtn) {
        submitBtn.disabled = false;
      }
    }
  });
});
