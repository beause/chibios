/**
 * itmstream.h
 *
 *  Created on: 2013-04-28
 *      Author: jeromeg
 */

#ifndef ITMSTREAM_H_
#define ITMSTREAM_H_

extern BaseSequentialStream ITMStream;

#define itmprintf(args...) chprintf(&ITMStream, args )

#endif /* ITMSTREAM_H_ */
