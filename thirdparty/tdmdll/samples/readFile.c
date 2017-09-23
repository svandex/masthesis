//-----------------------------------------------------------------------------
//
//	This sample program shows how to read a DIAdem file.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include "nilibddc.h"
#include <stdlib.h>
#include <stdio.h>

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define ddcChk(f) if (ddcError = (f), ddcError < 0) goto Error; else
#ifdef nullChk
#undef nullChk
#endif
#define nullChk(p) if (!(p)) { ddcError = DDC_OutOfMemory; goto Error; } else

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
static const char * FILE_PATH		= ".\\sampleFile.tdm";

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
static int	ReadFile		(void);
static int	ReadGroups		(DDCFileHandle file);
static int	ReadChannels 	(DDCChannelGroupHandle group);
double 		GetAvgDataValue (unsigned __int64 numDataValues, double *data);

//-----------------------------------------------------------------------------
// Program entry-point function
//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	int	ddcError = 0;

	ddcChk (ReadFile());

Error:
	if (ddcError < 0)
		printf ("\nError: %s\n", DDC_GetLibraryErrorDescription(ddcError));
	else
		printf ("\nNo errors.\n");
	printf("End of program, press Enter key to quit\n");
	getchar();
	return 0;
}

//-----------------------------------------------------------------------------
// Helper functions
//-----------------------------------------------------------------------------

// Reads the file
static int ReadFile (void)
{
	int				ddcError = 0, length;
	DDCFileHandle	file = 0;
	char			*property = 0;

	// Read file name
	ddcChk (DDC_OpenFileEx (FILE_PATH, "TDM", 1, &file));
	ddcChk (DDC_GetFileStringPropertyLength (file, DDC_FILE_NAME, &length));
	nullChk (property = malloc (length + 1));
	ddcChk (DDC_GetFileProperty (file, DDC_FILE_NAME, property, length + 1));

	printf ("File name property: %s\n", property);
	free (property);
	property = 0;

	// Read file description, if present
	if (DDC_GetFileStringPropertyLength (file, DDC_FILE_DESCRIPTION, &length) >= 0)
		{
		nullChk (property = malloc (length + 1));
		ddcChk (DDC_GetFileProperty (file, DDC_FILE_DESCRIPTION, property, length + 1));

		printf ("File description property: %s\n", property);
		free (property);
		property = 0;
		}

	// Read the channel groups
	ddcChk (ReadGroups (file));

Error:
	if (property)
		free (property);
	if (file)
		DDC_CloseFile (file);
	return ddcError;
}

// Reads all the channel groups in a file
static int ReadGroups (DDCFileHandle file)
{
	int						ddcError = 0, length;
	unsigned int			i, numGroups;
	DDCChannelGroupHandle	*groups = 0;
	char					*property = 0;

	// Get all the channel groups
	ddcChk (DDC_GetNumChannelGroups (file, &numGroups));
	nullChk (groups = calloc (numGroups, sizeof (DDCChannelGroupHandle)));
	ddcChk (DDC_GetChannelGroups (file, groups, numGroups));

	for (i = 0; i < numGroups; ++i)
		{
		// Read the channel group name
		ddcChk (DDC_GetChannelGroupStringPropertyLength (groups[i], DDC_CHANNELGROUP_NAME,
			&length));
		nullChk (property = malloc (length + 1));
		ddcChk (DDC_GetChannelGroupProperty (groups[i], DDC_CHANNELGROUP_NAME,
			property, length + 1));

		printf ("\n");
		printf ("Channelgroup #%d name property: %s\n", i+1, property);
		free (property);
		property = 0;

		// Read the channel group description, if present
		if (DDC_GetChannelGroupStringPropertyLength (groups[i],
			DDC_CHANNELGROUP_DESCRIPTION, &length) >= 0)
			{
			nullChk (property = malloc (length + 1));
			ddcChk (DDC_GetChannelGroupProperty (groups[i], DDC_CHANNELGROUP_DESCRIPTION,
				property, length + 1));

			printf ("Channelgroup #%d description property: %s\n", i+1, property);
			free (property);
			property = 0;
			}

		// Read the channels in this group
		ddcChk (ReadChannels (groups[i]));
		}

Error:
	// Cleanup
	if (groups)
		free (groups);
	if (property)
		free (property);
	return ddcError;
}

// Reads all the channels in a channel group
static int ReadChannels (DDCChannelGroupHandle group)
{
	int						ddcError = 0, length;
	unsigned int			i, numChannels;
	unsigned __int64		numDataValues;
	DDCChannelHandle		*channels = 0;
	char					*property = 0;
	double					*data = 0, avgDataValue;

	// Read all the channels in this channel group
	ddcChk (DDC_GetNumChannels (group, &numChannels));
	nullChk (channels = calloc (numChannels, sizeof (DDCChannelHandle)));
	ddcChk (DDC_GetChannels (group, channels, numChannels));

	for (i = 0; i < numChannels; ++i)
		{
		// Read the channel name
		ddcChk (DDC_GetChannelStringPropertyLength (channels[i], DDC_CHANNEL_NAME, &length));
		nullChk (property = malloc (length + 1));
		ddcChk (DDC_GetChannelProperty (channels[i], DDC_CHANNEL_NAME, property, length + 1));

		printf ("\n");
		printf ("Channel #%d name property: %s\n", i+1, property);
		free (property);
		property = 0;

		// Read the channel description, if present
		if (DDC_GetChannelStringPropertyLength (channels[i], DDC_CHANNEL_DESCRIPTION, &length) >= 0)
			{
			nullChk (property = malloc (length + 1));
			ddcChk (DDC_GetChannelProperty (channels[i], DDC_CHANNEL_DESCRIPTION,
				property, length + 1));

			printf ("Channel #%d description property: %s\n", i+1, property);
			free (property);
			property = 0;
			}

		// Read the channel units, if present
		if (DDC_GetChannelStringPropertyLength (channels[i], DDC_CHANNEL_UNIT_STRING, &length) >= 0)
			{
			nullChk (property = malloc (length + 1));
			ddcChk (DDC_GetChannelProperty (channels[i], DDC_CHANNEL_UNIT_STRING,
				property, length + 1));

			printf ("Channel #%d unit string property: %s\n", i+1, property);
			free (property);
			property = 0;
			}

		// Read the channel data
		ddcChk (DDC_GetNumDataValues (channels[i], &numDataValues));
		nullChk (data = malloc (sizeof (double) * (unsigned int)numDataValues));
		ddcChk (DDC_GetDataValues (channels[i], 0, (unsigned int)numDataValues, data));
		avgDataValue = GetAvgDataValue (numDataValues, data);

		printf ("Channel #%d number of data values: %I64d\n", i+1, numDataValues);
		printf ("Channel #%d average data value: %.2f\n", i+1, avgDataValue);
		free (data);
		data = 0;
	}

Error:
	// Cleanup
	if (data)
		free (data);
	if (channels)
		free (channels);
	if (property)
		free (property);
	return ddcError;
}

double GetAvgDataValue (unsigned __int64 numDataValues, double *data)
{
	int 	i;
	double 	sum = 0.0;

	for (i = 0; i < numDataValues; i++)
		sum += data[i];

	return sum / (unsigned int)numDataValues;
}
