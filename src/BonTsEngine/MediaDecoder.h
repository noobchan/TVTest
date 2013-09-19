// MediaDecoder.h: CMediaDecoder �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#pragma once


#include "Common.h"
#include "BonBaseClass.h"
#include "MediaData.h"
#include "TsUtilClass.h"


//////////////////////////////////////////////////////////////////////
// ���f�B�A�f�R�[�_���N���X
//////////////////////////////////////////////////////////////////////

class ABSTRACT_CLASS_DECL CMediaDecoder : public CBonBaseClass
{
public:
	class ABSTRACT_CLASS_DECL IEventHandler
	{
	public:
		virtual const DWORD OnDecoderEvent(CMediaDecoder *pDecoder, const DWORD dwEventID, PVOID pParam) = 0;
	};

	CMediaDecoder(IEventHandler *pEventHandler = NULL, const DWORD dwInputNum = 1UL, const DWORD dwOutputNum = 1UL);
	virtual ~CMediaDecoder() = 0;

	virtual void Reset(void);
	virtual void ResetGraph(void);

	virtual const DWORD GetInputNum(void) const;
	virtual const DWORD GetOutputNum(void) const;

	const bool SetOutputDecoder(CMediaDecoder *pDecoder, const DWORD dwOutputIndex = 0UL, const DWORD dwInputIndex = 0UL);
	virtual const bool InputMedia(CMediaData *pMediaData, const DWORD dwInputIndex = 0UL);

protected:
	const bool OutputMedia(CMediaData *pMediaData, const DWORD dwOutptIndex = 0UL);
	void ResetDownstreamDecoder(void);
	const DWORD SendDecoderEvent(const DWORD dwEventID, PVOID pParam = NULL);

	// �o�̓s���f�[�^�x�[�X
	struct TAG_OUTPUTDECODER
	{
		CMediaDecoder *pDecoder;
		DWORD dwInputIndex;
	} m_aOutputDecoder[4];

	IEventHandler *m_pEventHandler;

	const DWORD m_dwInputNum;
	const DWORD m_dwOutputNum;

	mutable CCriticalLock m_DecoderLock;
};