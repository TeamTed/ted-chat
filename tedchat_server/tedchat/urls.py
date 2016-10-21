#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 cknapp <cknapp@mbp.local>
#
# Distributed under terms of the MIT license.

from django.conf.urls import url, include
from django.contrib import admin

from . import views

urlpatterns = [
    url(r'^jwt', views.issue_jwt_view),
    url(r'^post', views.post_message_view),
    url(r'^get', views.retrieve_message_view),
    url(r'^register', views.register_account_view),    
]
