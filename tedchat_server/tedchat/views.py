from datetime import datetime 

from django.shortcuts import render
from django.contrib.auth.models import User

import jwt
from rest_framework_jwt.settings import api_settings

#from django.http import HttpResponse #we're always going to respond with a
                                      #Json response so we don't need this
from django.http import JsonResponse

from models import Message

from rest_framework_jwt.authentication import BaseJSONWebTokenAuthentication

datetime_format = '%d/%m/%Y %H:%M:%S'

def check_jwt(jwt_string):
    """
    returns the USERNAME if valid, False otherwise
    """

    if jwt_string is None:
        return None, {
            'error' : 'no jwt provided'
        }
        
    jwt_decode_handler = api_settings.JWT_DECODE_HANDLER
    jwt_get_username_from_payload = \
        api_settings.JWT_PAYLOAD_GET_USERNAME_HANDLER
    
    try:
        payload = jwt_decode_handler(jwt_string)
    except jwt.ExpiredSignature:
        return None, {
            'error' : 'jwt expired'
        }
    except jwt.DecodeError:
        return None,{
            'error' : 'decoding error'
        }
    except jwt.InvalidTokenError:
        return None, {
            'error' : 'invalid token'
        }
    
    authenticator = BaseJSONWebTokenAuthentication()
    user = authenticator.authenticate_credentials(payload)
    return user, None

def issue_jwt_view(request):
    username = request.POST.get("username", None)
    password = request.POST.get("password", None)

    if not username:
        return JsonResponse({
            'error' : 'no username provided (key: username)'
        })
    if not password:
        return JsonResponse({
            'error' : 'no password provided (key: password)'
        })

    try:
        user_object = User.objects.get(username=username)
    except User.DoesNotExist:
         return JsonResponse({
            'error' : 'unknown user'
        })

    if user_object.check_password(password) is False:
        return JsonResponse({
            'error' : 'incorrect password'
        })

    jwt_payload_handler = api_settings.JWT_PAYLOAD_HANDLER
    jwt_encode_handler = api_settings.JWT_ENCODE_HANDLER

    payload = jwt_payload_handler(user_object)
    token = jwt_encode_handler(payload)
    return JsonResponse({
        'jwt' : token,
        })

def post_message_view(request):
    jwt = request.POST.get("jwt", None)
    user,jwt_error_json = check_jwt(jwt)
    if(user is None):
        return JsonResponse(jwt_error_json)

    message_text = request.POST.get("text", False)
    message_sender = user
    message_receiver = request.POST.get("receiver", False)

    if(message_text is False):
        return JsonResponse({
            'error' : 'no message text (key: text)'
        })
    if(message_receiver is False):
        return JsonResponse({
            'error' : 'no message receiver (key: receiver)'
        })

    message = Message(text = message_text,
            sender = message_sender,
            receiver = message_receiver,
            pub_date=datetime.now())

    message.save()

    return JsonResponse({
        'status' : 'success'
    })
    
def retrieve_message_view(request):
    jwt = request.POST.get("jwt", None)
    user,jwt_error_json = check_jwt(jwt)
    if(user is None):
        return JsonResponse(jwt_error_json)

    start_datetime_str = request.POST.get("after", False)

    if( start_datetime_str is False ):
        my_messages_obj_list = Message.objects.filter(receiver=user)
    else:
        my_messages_obj_list = Message.objects.filter(
                receiver=user,
                pud_date__gte = datetime.strptime(
                    start_datetime_str, datetime_format
                    )
                )

    my_message_json_list = []    
    for msg_obj in my_messages_obj_list:
        my_message_json_list.append({
            'text' : msg_obj.text,
            'sender' : msg_obj.sender,
            'receiver' : msg_obj.receiver,
            'pub_date' : msg_obj.pub_date.strftime(datetime_format),
            'id' : msg_obj.id
            })

    return JsonResponse({
        'messages' : my_message_json_list
    })

        
def register_account_view(request):
    username = request.POST.get('username', None)
    password = request.POST.get('password', None)
    email = request.POST.get('email', None)

    if username and password and email:
        u, created = User.objects.get_or_create(
                username=username)
        if created:
            u.set_password(password)
            u.email = email
            u.save()
            return JsonResponse({
                'status' : 'success'
            })

        else:
            return JsonResponse({
                'error' : 'username unavailable'
            })
    else:
        if not username:
            return JsonResponse({
                'error' : 'no username provided (key: username)'
            })
        if not password:
            return JsonResponse({
                'error' : 'no password provided (key: password)'
            })
        if not email:
            return JsonResponse({
                'error' : 'no email provided (key: email)'
            })

