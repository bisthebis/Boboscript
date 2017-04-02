#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

class QString;

/**
 * @brief Takes a filepath of a Boboscript source file (filename.bs) and write the output to a json file (filename_tokens.bs)
 * @param path : Path of the file to tokenize
 */
void tokenizeFile(const QString& path);

#endif // COMMAND_LINE_H
