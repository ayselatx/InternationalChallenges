# accounts/views.py
from django.contrib.auth.forms import UserCreationForm, PasswordChangeForm
from django.urls import reverse_lazy
from django.views.generic import CreateView
from django.contrib.auth.views import (
    PasswordChangeView as BasePasswordChangeView,
    PasswordChangeDoneView as BasePasswordChangeDoneView,
)

# These views are heavily based on Django's defaults (the forms come from Django).
# If we'd like to change it or style it better, we should probably create custom forms
# which extend the original ones and then use them in these views. I haven't done it before,
# I guess it needs a few good google searches if you want to get it right.

class SignUpView(CreateView):
    form_class = UserCreationForm
    success_url = reverse_lazy("login")
    template_name = "registration/signup.html"


class PasswordChangeView(BasePasswordChangeView):
    success_url = reverse_lazy("password_change_done")
    template_name = "registration/password_change_form.html"


class PasswordChangeDoneView(BasePasswordChangeDoneView):
    template_name = "registration/password_change_done.html"
