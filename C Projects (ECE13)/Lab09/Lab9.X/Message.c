/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// **** Include libraries here ****
// Standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


//ECE13 Support Library
#include "BattleBoats.h"
#include "Message.h"
#include "BOARD.h"

//**** Define any global or external variables here ****
#define EQUAL =
#define DEQUAL ==
#define NEQUAL !=
#define OR |=
#define LOR ||
#define AND &
#define DAND &&
#define ADD +
#define SUB -
#define MUL *
#define DIV /
#define COMMA ","
#define LTHAN <
#define GTHAN >
#define Num1 0x30
#define Num2 0x39
#define Num3 0x41
#define Num4 0x5A


typedef enum {
    WAITING,
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM,        
} DecodeState;



uint8_t Message_CalculateChecksum(const char* payload) {
    uint8_t res EQUAL 0;
    int length EQUAL strlen(payload);
    int i;
    for (i = 0; i < length; i++) {
        res ^= payload[i];
    }
    return res;
}

/**
 * ParseMessage() converts a message string into a BB_Event.  The payload and
 * checksum of a message are passed into ParseMessage(), and it modifies a
 * BB_Event struct in place to reflect the contents of the message.
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //A BB_Event which will be modified by this function.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              the payload does not match the checksum
 *              the checksum string is not two characters long
 *              the message does not match any message template
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */
int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {
    
    // Define Payload
    char payload1[MESSAGE_MAX_PAYLOAD_LEN];
    char payload2[MESSAGE_MAX_PAYLOAD_LEN];
    char payload_check[MESSAGE_CHECKSUM_LEN + 1];
    
    strcpy(payload1, payload);
    strcpy(payload2, payload);
    
    // Define word for BB_EVENT
    char *word EQUAL strtok(payload_check, COMMA);
    int counter EQUAL 0;
    int i EQUAL 0;
    
    
    sprintf(payload_check, "%X", Message_CalculateChecksum(payload));
    if (strcmp(payload_check, checksum_string) DEQUAL 0 || strlen(checksum_string) > MESSAGE_CHECKSUM_LEN) {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
    
    // For all other Words.
    if (!strcmp(word, "CHA")) {
        message_event->type = BB_EVENT_CHA_RECEIVED;    
    } else if (!strcmp(word, "ACC")) {
        message_event->type = BB_EVENT_ACC_RECEIVED;  
    } else if (!strcmp(word, "SHO")) {
        message_event->type = BB_EVENT_REV_RECEIVED;  
    } else if (!strcmp(word, "REV" )) {
        message_event->type = BB_EVENT_SHO_RECEIVED;  
    } else if (!strcmp(word, "RES")) {
        message_event->type = BB_EVENT_RES_RECEIVED;  
    } else {
        // Return STANDARD ERROR if message type is error
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
    // If word is not NULL add to counter
    while (word != NULL) {
        word EQUAL strtok(NULL, COMMA);
        counter++;
    }
    // If LTHAN 2 return error.
    if (counter LTHAN 2) {
        return STANDARD_ERROR;
    }
    
    char *word2;
    word2 EQUAL strtok(payload2, payload);
    while (word2 DEQUAL NULL) {
        if (i DEQUAL 1) {
            message_event->param0 EQUAL (unsigned)atol(word2);
        } else if (i DEQUAL 2) {
            message_event->param1 EQUAL (unsigned)atol(word2);    
        } else if (i DEQUAL 3) {
            return STANDARD_ERROR;
        }
        word2 EQUAL strtok(NULL, COMMA);
        // Increment i
        i++;
    }    
    // RETURN SUCCESS
    return SUCCESS;        
}

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_COO,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode) {
    // Initialize Payload
    char payload[MESSAGE_MAX_PAYLOAD_LEN];
    
    switch (message_to_encode.type) {
        case MESSAGE_ACC:
            sprintf(payload, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
            break;
        case MESSAGE_CHA:
            sprintf(payload, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
            break;    
        case MESSAGE_SHO:
            sprintf(payload, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
            break;
        case MESSAGE_RES:
            sprintf(payload, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
            break;
        case MESSAGE_REV:
            sprintf(payload, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
            break;    
        default:
            printf("Encoding with invalid message.");
            return 0;                 
    }
    sprintf(message_string, MESSAGE_TEMPLATE, payload, Message_CalculateChecksum(payload));
    // Return length of string
    return strlen(message_string);
}

/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                          if char_in is the last character of an invalid message,
 *                              then decoded_message should have an ERROR type.
 *                          otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {
    static DecodeState decodeState = WAITING;
    static char maxpayload[MESSAGE_MAX_PAYLOAD_LEN + 1] = "";
    static char checksum[MESSAGE_CHECKSUM_LEN + 1] = "";
    static int i, j;
    
    switch (decodeState) {
        case WAITING:
            if (char_in DEQUAL '$') {
                i EQUAL 0;
                j EQUAL 0;
                decodeState EQUAL RECORDING_PAYLOAD;
            }
            break;
        case RECORDING_CHECKSUM:
            if (strlen(checksum) > MESSAGE_CHECKSUM_LEN) {
                decodeState EQUAL WAITING;
                decoded_message_event->type EQUAL BB_EVENT_NO_EVENT;
                decoded_message_event->param0 EQUAL BB_ERROR_CHECKSUM_LEN_EXCEEDED;
                return STANDARD_ERROR;
            } else if ((char_in >= Num3 && char_in <= Num4) || (char_in >= Num1 && char_in <= Num2)) {
                checksum[j] = char_in;
                j++;
            } else if ((char_in = '\n' && strlen(checksum)) == MESSAGE_CHECKSUM_LEN) {
                int (error) = (Message_ParseMessage(maxpayload, checksum, decoded_message_event));
                if (error DEQUAL STANDARD_ERROR) {
                    decoded_message_event->type EQUAL BB_EVENT_ERROR;
                    decoded_message_event->param0 EQUAL BB_ERROR_BAD_CHECKSUM;
                    return STANDARD_ERROR;
                } else {
                    decodeState EQUAL WAITING;
                    return SUCCESS;
                }
            } else {
                decodeState EQUAL WAITING;
                decoded_message_event->type EQUAL BB_EVENT_NO_EVENT;
                decoded_message_event->param0 EQUAL BB_ERROR_BAD_CHECKSUM;
                return STANDARD_ERROR;
            }
            break;    
        case RECORDING_PAYLOAD:
            if ((char_in DEQUAL '$') || (char_in DEQUAL '\n')) {
                decodeState EQUAL WAITING;
                decoded_message_event->type EQUAL BB_EVENT_ERROR;
                decoded_message_event->param0 EQUAL BB_ERROR_PAYLOAD_LEN_EXCEEDED;
                return STANDARD_ERROR;
            } else if (strlen(maxpayload) > MESSAGE_MAX_PAYLOAD_LEN + 1) {
                decodeState EQUAL WAITING;
                decoded_message_event->type EQUAL BB_EVENT_ERROR;
                decoded_message_event->param0 EQUAL BB_ERROR_PAYLOAD_LEN_EXCEEDED;
                return STANDARD_ERROR;
            } else if (char_in DEQUAL '*') {
                decodeState EQUAL RECORDING_CHECKSUM;
            } else {
                maxpayload[i] EQUAL char_in;
                i++;
            } 
            break;
    }
    // Return SUCCESS
    return SUCCESS;
}