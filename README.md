
#  Cinema Sansaar
 
Cinema Sansaar is a simple movie ticket booking system prototype developed using Qt Creator, a C++ framework. The application allows users to  select  tickets for their desired movies .

# Features
- **User Signup**: Users can sign up for a cinema membership by providing their username, email, password, and a verification code sent to their email.(users should be registered in the domain of the owner.)
- **Email Verification**: The application uses Mailgun to send a verification code to the user's email for verification during signup.
- **Local Database**: SQLite is used for local storage to store user information securely.
- **Internet Access**: Internet access is required during the signup process to send and receive verification emails.
- **Smooth User Experience**: Cinema Sansaar has a smooth UI which improves your experiene
  

# Requirements
To use this project, you need:
- Your own Mailgun API key and domain for sending verification emails.
- Qt Creator installed on your system.
- Internet access to sign up for a cinema membership.


# Contributors
- [Aashutosh Upadhyaya Sapkota](https://github.com/ASU-N)
- Risham Raj (Byahut)
- Saimon Neupane
  

# How to use this project
Its simple just clone our project and you can run it on your QT Creator.For default use 'users' 'user' i.e username and password for login.
For signup purpose you need to create your own Mailgun API Key and enter the Domain .In order to get verification code user's gmail id should
be reigsterd in your domain.
