#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>

static DBusConnection *connection;
static DBusError error;

void dbus_setup() {
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Couldn't connect to session bus: %s\n", error.message);
        dbus_error_free(&error);
        exit(1);
    }
}

void dbus_update_sb() {
    DBusMessage *message;
    DBusPendingCall *pending;

    // A status bar service with a method Update to refresh the status bar.
    message = dbus_message_new_method_call(
        "org.user.StatusBar",
        "/org/user/StatusBar",
        "org.user.StatusBar",
        "Update"
    );

    dbus_connection_send_with_reply(connection, message, &pending, -1);

    if (pending == NULL) {
        fprintf(stderr, "Could not send D-Bus method call.\n");
    }

    dbus_connection_flush(connection);

    dbus_message_unref(message);
    dbus_pending_call_unref(pending);
}