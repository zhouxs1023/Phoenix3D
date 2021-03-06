// PX2E_ResTreeItem.hpp

#ifndef PX2E_RESTREEITEM_HPP
#define PX2E_RESTREEITEM_HPP

#include "PX2EditorPre.hpp"
#include "PX2SmartPointer.hpp"

namespace PX2Editor
{

	class ResTree;

	class ResTreeItem
	{
	public:
		ResTreeItem(ResTree *resTree, std::string name, std::string pathName);
		~ResTreeItem();

		wxTreeItemId GetItemID() { return mItemID; }
		std::string GetName() { return mResName; }
		std::string GetPathName() { return mResPathName; }

		void RootBuild();
		void AddChild(ResTreeItem *item);
		int GetChildNum();
		bool IsTexPack() { return mIsTexPack; }
		void SetBeTexPackElement(bool isEle) { mIsTexPackElement = isEle; }
		bool IsTexPackElement() const { return mIsTexPackElement; };

		ResTreeItem *GetParent() { return mParent; }

		ResTreeItem *GetChildItem(wxTreeItemId id);
		ResTreeItem *GetChildItem(const std::string& resPath);

	public_internal:
		void SetParent(ResTreeItem *parent);
		void _BuildChild();
		bool _IsAFile(const std::string &filename);

	protected:
		ResTreeItem();

		ResTree *mResTree;

		wxTreeItemId mItemID;
		std::string mResName;
		std::string mResPathName;
		bool mIsTexPack;
		bool mIsTexPackElement;

		ResTreeItem *mParent;
		std::vector<PX2::Pointer0<ResTreeItem>> mChildItems;

		std::vector<PX2::Pointer0<ResTreeItem> > mChildFilesItems;
	};

	typedef PX2::Pointer0<ResTreeItem> ResTreeItemPtr;

}

#endif